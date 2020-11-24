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

Class
    Foam::timeVaryingSurfaceNormalFvPatchVectorField

Description
    This boundary condition provides a surface-normal vector boundary condition
    by its magnitude with temporal variation using a sinusoidal function.

Usage
    \table
        Property     | Description             | Required    | Default value
        refValue     | reference value         | yes         |
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            timeVaryingSurfaceNormal;
        refValue        uniform -10;           // 10 INTO the domain
    }
    \endverbatim

Note
    Sign conventions:
    - the value is positive for outward-pointing vectors

See also
    Foam::fixedValueFvPatchField

SourceFiles
    timeVaryingSurfaceNormalFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef timeVaryingSurfaceNormalFvPatchVectorField_H
#define timeVaryingSurfaceNormalFvPatchVectorField_H

#include "fvPatchFields.H"
#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
          Class timeVaryingSurfaceNormalFvPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class timeVaryingSurfaceNormalFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{
    // Private data

        scalarField refValue_;
        scalar t() const;

public:

    //- Runtime type information
    TypeName("timeVaryingSurfaceNormal");


    // Constructors

        //- Construct from patch and internal field
        timeVaryingSurfaceNormalFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        timeVaryingSurfaceNormalFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  timeVaryingSurfaceNormalFvPatchVectorField
        //  onto a new patch
        timeVaryingSurfaceNormalFvPatchVectorField
        (
            const timeVaryingSurfaceNormalFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        timeVaryingSurfaceNormalFvPatchVectorField
        (
            const timeVaryingSurfaceNormalFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new timeVaryingSurfaceNormalFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        timeVaryingSurfaceNormalFvPatchVectorField
        (
            const timeVaryingSurfaceNormalFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new timeVaryingSurfaceNormalFvPatchVectorField
                (
                    *this,
                    iF
                )
            );
        }


    // Member functions

        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchVectorField&,
                const labelList&
            );


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
