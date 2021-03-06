/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "timeVaryingSurfaceNormalFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "fvPatchFieldMapper.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::scalar Foam::timeVaryingSurfaceNormalFvPatchVectorField::t() const
{
    return db().time().timeOutputValue();
}

Foam::timeVaryingSurfaceNormalFvPatchVectorField::
timeVaryingSurfaceNormalFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    refValue_(p.size())
{}


Foam::timeVaryingSurfaceNormalFvPatchVectorField::
timeVaryingSurfaceNormalFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF, dict, false),
    refValue_("refValue", dict, p.size())
{
    fvPatchVectorField::operator=(refValue_*patch().nf()*sin(t()));
}


Foam::timeVaryingSurfaceNormalFvPatchVectorField::
timeVaryingSurfaceNormalFvPatchVectorField
(
    const timeVaryingSurfaceNormalFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(p, iF),
    refValue_(ptf.refValue_, mapper)
{
    // Note: calculate product only on ptf to avoid multiplication on
    // unset values in reconstructPar.
    fvPatchVectorField::operator=
    (
        vectorField
        (
            ptf.refValue_*ptf.patch().nf()*sin(ptf.t()),
            mapper
        )
    );
}


Foam::timeVaryingSurfaceNormalFvPatchVectorField::
timeVaryingSurfaceNormalFvPatchVectorField
(
    const timeVaryingSurfaceNormalFvPatchVectorField& pivpvf
)
:
    fixedValueFvPatchVectorField(pivpvf),
    refValue_(pivpvf.refValue_)
{}


Foam::timeVaryingSurfaceNormalFvPatchVectorField::
timeVaryingSurfaceNormalFvPatchVectorField
(
    const timeVaryingSurfaceNormalFvPatchVectorField& pivpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(pivpvf, iF),
    refValue_(pivpvf.refValue_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::timeVaryingSurfaceNormalFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchVectorField::autoMap(m);
    refValue_.autoMap(m);
}


void Foam::timeVaryingSurfaceNormalFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchVectorField::rmap(ptf, addr);

    const timeVaryingSurfaceNormalFvPatchVectorField& tiptf =
        refCast<const timeVaryingSurfaceNormalFvPatchVectorField>(ptf);

    refValue_.rmap(tiptf.refValue_, addr);
}


void Foam::timeVaryingSurfaceNormalFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    fvPatchVectorField::operator=(refValue_*patch().nf()*sin(t()));
    fvPatchVectorField::updateCoeffs();
}


void Foam::timeVaryingSurfaceNormalFvPatchVectorField::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
    refValue_.writeEntry("refValue", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        timeVaryingSurfaceNormalFvPatchVectorField
    );
}

// ************************************************************************* //
